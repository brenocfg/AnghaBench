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
typedef  size_t u8 ;
struct fman_keygen {TYPE_1__* schemes; } ;
struct TYPE_2__ {int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t FM_KG_MAX_NUM_OF_SCHEMES ; 

__attribute__((used)) static int get_free_scheme_id(struct fman_keygen *keygen, u8 *scheme_id)
{
	u8 i;

	for (i = 0; i < FM_KG_MAX_NUM_OF_SCHEMES; i++)
		if (!keygen->schemes[i].used) {
			*scheme_id = i;
			return 0;
		}

	return -EINVAL;
}