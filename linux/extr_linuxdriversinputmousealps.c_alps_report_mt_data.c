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
struct psmouse {struct input_dev* dev; struct alps_data* private; } ;
struct input_dev {int dummy; } ;
struct alps_fields {TYPE_1__* mt; } ;
struct alps_data {struct alps_fields f; } ;
struct TYPE_2__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int MAX_TOUCHES ; 
 int /*<<< orphan*/  alps_set_slot (struct input_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_mt_assign_slots (struct input_dev*,int*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_mt_sync_frame (struct input_dev*) ; 

__attribute__((used)) static void alps_report_mt_data(struct psmouse *psmouse, int n)
{
	struct alps_data *priv = psmouse->private;
	struct input_dev *dev = psmouse->dev;
	struct alps_fields *f = &priv->f;
	int i, slot[MAX_TOUCHES];

	input_mt_assign_slots(dev, slot, f->mt, n, 0);
	for (i = 0; i < n; i++)
		alps_set_slot(dev, slot[i], f->mt[i].x, f->mt[i].y);

	input_mt_sync_frame(dev);
}