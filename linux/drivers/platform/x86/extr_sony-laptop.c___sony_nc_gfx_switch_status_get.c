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
struct TYPE_2__ {int handle; } ;

/* Variables and functions */
 int AUTO ; 
 int EINVAL ; 
 int EIO ; 
 int SPEED ; 
 int STAMINA ; 
 int /*<<< orphan*/  dprintk (char*,unsigned int) ; 
 TYPE_1__* gfxs_ctl ; 
 scalar_t__ sony_call_snc_handle (int,int,unsigned int*) ; 

__attribute__((used)) static int __sony_nc_gfx_switch_status_get(void)
{
	unsigned int result;

	if (sony_call_snc_handle(gfxs_ctl->handle,
				gfxs_ctl->handle == 0x015B ? 0x0000 : 0x0100,
				&result))
		return -EIO;

	switch (gfxs_ctl->handle) {
	case 0x0146:
		/* 1: discrete GFX (speed)
		 * 0: integrated GFX (stamina)
		 */
		return result & 0x1 ? SPEED : STAMINA;
		break;
	case 0x015B:
		/* 0: discrete GFX (speed)
		 * 1: integrated GFX (stamina)
		 */
		return result & 0x1 ? STAMINA : SPEED;
		break;
	case 0x0128:
		/* it's a more elaborated bitmask, for now:
		 * 2: integrated GFX (stamina)
		 * 0: discrete GFX (speed)
		 */
		dprintk("GFX Status: 0x%x\n", result);
		return result & 0x80 ? AUTO :
			result & 0x02 ? STAMINA : SPEED;
		break;
	}
	return -EINVAL;
}