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
struct TYPE_5__ {int num_urb; int /*<<< orphan*/  stream_started; TYPE_3__** urb; int /*<<< orphan*/ * transfer_buffer; } ;
struct em28xx {TYPE_2__ adev; TYPE_1__* intf; } ;
struct TYPE_6__ {int /*<<< orphan*/  transfer_buffer_length; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  em28xx_deinit_isoc_audio (struct em28xx*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int em28xx_init_audio_isoc(struct em28xx *dev)
{
	int       i, err;

	dprintk("Starting isoc transfers\n");

	/* Start streaming */
	for (i = 0; i < dev->adev.num_urb; i++) {
		memset(dev->adev.transfer_buffer[i], 0x80,
		       dev->adev.urb[i]->transfer_buffer_length);

		err = usb_submit_urb(dev->adev.urb[i], GFP_ATOMIC);
		if (err) {
			dev_err(&dev->intf->dev,
				"submit of audio urb failed (error=%i)\n",
				err);
			em28xx_deinit_isoc_audio(dev);
			atomic_set(&dev->adev.stream_started, 0);
			return err;
		}
	}

	return 0;
}