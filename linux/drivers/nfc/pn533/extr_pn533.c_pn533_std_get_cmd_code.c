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
typedef  int /*<<< orphan*/  u8 ;
struct pn533_std_frame {int dummy; } ;
typedef  struct pn533_std_frame pn533_ext_frame ;

/* Variables and functions */
 int /*<<< orphan*/  PN533_FRAME_CMD (struct pn533_std_frame*) ; 
 scalar_t__ PN533_STD_IS_EXTENDED (struct pn533_std_frame*) ; 

__attribute__((used)) static u8 pn533_std_get_cmd_code(void *frame)
{
	struct pn533_std_frame *f = frame;
	struct pn533_ext_frame *eif = frame;

	if (PN533_STD_IS_EXTENDED(f))
		return PN533_FRAME_CMD(eif);
	else
		return PN533_FRAME_CMD(f);
}