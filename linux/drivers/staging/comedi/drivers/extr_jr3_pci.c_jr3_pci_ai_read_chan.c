#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct jr3_pci_subdev_private {scalar_t__ state; TYPE_2__* sensor; } ;
struct comedi_subdevice {struct jr3_pci_subdev_private* private; } ;
struct comedi_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  serial_no; int /*<<< orphan*/  model_no; TYPE_1__* filter; } ;
struct TYPE_3__ {int /*<<< orphan*/  v2; int /*<<< orphan*/  v1; int /*<<< orphan*/  mz; int /*<<< orphan*/  my; int /*<<< orphan*/  mx; int /*<<< orphan*/  fz; int /*<<< orphan*/  fy; int /*<<< orphan*/  fx; } ;

/* Variables and functions */
 unsigned int get_s16 (int /*<<< orphan*/ *) ; 
 unsigned int get_u16 (int /*<<< orphan*/ *) ; 
 scalar_t__ state_jr3_done ; 

__attribute__((used)) static unsigned int jr3_pci_ai_read_chan(struct comedi_device *dev,
					 struct comedi_subdevice *s,
					 unsigned int chan)
{
	struct jr3_pci_subdev_private *spriv = s->private;
	unsigned int val = 0;

	if (spriv->state != state_jr3_done)
		return 0;

	if (chan < 56) {
		unsigned int axis = chan % 8;
		unsigned int filter = chan / 8;

		switch (axis) {
		case 0:
			val = get_s16(&spriv->sensor->filter[filter].fx);
			break;
		case 1:
			val = get_s16(&spriv->sensor->filter[filter].fy);
			break;
		case 2:
			val = get_s16(&spriv->sensor->filter[filter].fz);
			break;
		case 3:
			val = get_s16(&spriv->sensor->filter[filter].mx);
			break;
		case 4:
			val = get_s16(&spriv->sensor->filter[filter].my);
			break;
		case 5:
			val = get_s16(&spriv->sensor->filter[filter].mz);
			break;
		case 6:
			val = get_s16(&spriv->sensor->filter[filter].v1);
			break;
		case 7:
			val = get_s16(&spriv->sensor->filter[filter].v2);
			break;
		}
		val += 0x4000;
	} else if (chan == 56) {
		val = get_u16(&spriv->sensor->model_no);
	} else if (chan == 57) {
		val = get_u16(&spriv->sensor->serial_no);
	}

	return val;
}