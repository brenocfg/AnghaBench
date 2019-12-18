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
typedef  int /*<<< orphan*/  u16 ;
struct vc_data {int /*<<< orphan*/  vc_video_erase_char; } ;
struct sisusb_usb_data {int sisusb_num_columns; int /*<<< orphan*/  lock; } ;
typedef  enum con_scroll { ____Placeholder_con_scroll } con_scroll ;

/* Variables and functions */
#define  SM_DOWN 129 
#define  SM_UP 128 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sisusb_copy_memory (struct sisusb_usb_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sisusb_haddr (struct sisusb_usb_data*,struct vc_data*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sisusb_vaddr (struct sisusb_usb_data*,struct vc_data*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sisusbcon_memsetw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static bool
sisusbcon_scroll_area(struct vc_data *c, struct sisusb_usb_data *sisusb,
		unsigned int t, unsigned int b, enum con_scroll dir,
		unsigned int lines)
{
	int cols = sisusb->sisusb_num_columns;
	int length = ((b - t) * cols) * 2;
	u16 eattr = c->vc_video_erase_char;

	/* sisusb->lock is down */

	/* Scroll an area which does not match the
	 * visible screen's dimensions. This needs
	 * to be done separately, as it does not
	 * use hardware panning.
	 */

	switch (dir) {

		case SM_UP:
			memmove(sisusb_vaddr(sisusb, c, 0, t),
					   sisusb_vaddr(sisusb, c, 0, t + lines),
					   (b - t - lines) * cols * 2);
			sisusbcon_memsetw(sisusb_vaddr(sisusb, c, 0, b - lines),
					eattr, lines * cols * 2);
			break;

		case SM_DOWN:
			memmove(sisusb_vaddr(sisusb, c, 0, t + lines),
					   sisusb_vaddr(sisusb, c, 0, t),
					   (b - t - lines) * cols * 2);
			sisusbcon_memsetw(sisusb_vaddr(sisusb, c, 0, t), eattr,
					  lines * cols * 2);
			break;
	}

	sisusb_copy_memory(sisusb, sisusb_vaddr(sisusb, c, 0, t),
			sisusb_haddr(sisusb, c, 0, t), length);

	mutex_unlock(&sisusb->lock);

	return true;
}