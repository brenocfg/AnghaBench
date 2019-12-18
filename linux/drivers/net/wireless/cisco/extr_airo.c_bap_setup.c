#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct airo_info {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int BAP_BUSY ; 
 int BAP_DONE ; 
 int BAP_ERR ; 
 int ERROR ; 
 int IN4500 (struct airo_info*,scalar_t__) ; 
 scalar_t__ OFFSET0 ; 
 int /*<<< orphan*/  OUT4500 (struct airo_info*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SELECT0 ; 
 int SUCCESS ; 
 int /*<<< orphan*/  airo_print_err (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int bap_setup(struct airo_info *ai, u16 rid, u16 offset, int whichbap )
{
	int timeout = 50;
	int max_tries = 3;

	OUT4500(ai, SELECT0+whichbap, rid);
	OUT4500(ai, OFFSET0+whichbap, offset);
	while (1) {
		int status = IN4500(ai, OFFSET0+whichbap);
		if (status & BAP_BUSY) {
                        /* This isn't really a timeout, but its kinda
			   close */
			if (timeout--) {
				continue;
			}
		} else if ( status & BAP_ERR ) {
			/* invalid rid or offset */
			airo_print_err(ai->dev->name, "BAP error %x %d",
				status, whichbap );
			return ERROR;
		} else if (status & BAP_DONE) { // success
			return SUCCESS;
		}
		if ( !(max_tries--) ) {
			airo_print_err(ai->dev->name,
				"BAP setup error too many retries\n");
			return ERROR;
		}
		// -- PC4500 missed it, try again
		OUT4500(ai, SELECT0+whichbap, rid);
		OUT4500(ai, OFFSET0+whichbap, offset);
		timeout = 50;
	}
}