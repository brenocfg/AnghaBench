#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8 ;
struct dst_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_CA_NOTICE ; 
 int EIO ; 
 scalar_t__ RETRIES ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ dst_ci_command (struct dst_state*,scalar_t__*,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  dst_error_recovery (struct dst_state*) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int dst_put_ci(struct dst_state *state, u8 *data, int len, u8 *ca_string, int read)
{
	u8 dst_ca_comm_err = 0;

	while (dst_ca_comm_err < RETRIES) {
		dprintk(verbose, DST_CA_NOTICE, 1, " Put Command");
		if (dst_ci_command(state, data, ca_string, len, read)) {	// If error
			dst_error_recovery(state);
			dst_ca_comm_err++; // work required here.
		} else {
			break;
		}
	}

	if(dst_ca_comm_err == RETRIES)
		return -EIO;

	return 0;
}