#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int* status_ptr; int event_counter; int /*<<< orphan*/  event_wrap; } ;
typedef  TYPE_1__ drm_savage_private_t ;

/* Variables and functions */
 unsigned int BCI_CMD_UPDATE_EVENT_TAG ; 
 unsigned int BCI_CMD_WAIT ; 
 unsigned int BCI_CMD_WAIT_2D ; 
 unsigned int BCI_CMD_WAIT_3D ; 
 int /*<<< orphan*/  BCI_LOCALS ; 
 int /*<<< orphan*/  BCI_WRITE (unsigned int) ; 
 int /*<<< orphan*/  BEGIN_BCI (int) ; 
 unsigned int SAVAGE_WAIT_2D ; 
 unsigned int SAVAGE_WAIT_3D ; 

uint16_t savage_bci_emit_event(drm_savage_private_t * dev_priv,
			       unsigned int flags)
{
	uint16_t count;
	BCI_LOCALS;

	if (dev_priv->status_ptr) {
		/* coordinate with Xserver */
		count = dev_priv->status_ptr[1023];
		if (count < dev_priv->event_counter)
			dev_priv->event_wrap++;
	} else {
		count = dev_priv->event_counter;
	}
	count = (count + 1) & 0xffff;
	if (count == 0) {
		count++;	/* See the comment above savage_wait_event_*. */
		dev_priv->event_wrap++;
	}
	dev_priv->event_counter = count;
	if (dev_priv->status_ptr)
		dev_priv->status_ptr[1023] = (uint32_t) count;

	if ((flags & (SAVAGE_WAIT_2D | SAVAGE_WAIT_3D))) {
		unsigned int wait_cmd = BCI_CMD_WAIT;
		if ((flags & SAVAGE_WAIT_2D))
			wait_cmd |= BCI_CMD_WAIT_2D;
		if ((flags & SAVAGE_WAIT_3D))
			wait_cmd |= BCI_CMD_WAIT_3D;
		BEGIN_BCI(2);
		BCI_WRITE(wait_cmd);
	} else {
		BEGIN_BCI(1);
	}
	BCI_WRITE(BCI_CMD_UPDATE_EVENT_TAG | (uint32_t) count);

	return count;
}