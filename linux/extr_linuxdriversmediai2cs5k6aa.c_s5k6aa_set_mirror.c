#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* vflip; } ;
struct s5k6aa {unsigned int inv_vflip; int inv_hflip; TYPE_3__ ctrls; TYPE_1__* preset; int /*<<< orphan*/  sd; } ;
struct i2c_client {int dummy; } ;
struct TYPE_5__ {unsigned int val; } ;
struct TYPE_4__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_P_PREV_MIRROR (int) ; 
 int s5k6aa_write (struct i2c_client*,int /*<<< orphan*/ ,unsigned int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s5k6aa_set_mirror(struct s5k6aa *s5k6aa, int horiz_flip)
{
	struct i2c_client *client = v4l2_get_subdevdata(&s5k6aa->sd);
	int index = s5k6aa->preset->index;

	unsigned int vflip = s5k6aa->ctrls.vflip->val ^ s5k6aa->inv_vflip;
	unsigned int flip = (horiz_flip ^ s5k6aa->inv_hflip) | (vflip << 1);

	return s5k6aa_write(client, REG_P_PREV_MIRROR(index), flip);
}