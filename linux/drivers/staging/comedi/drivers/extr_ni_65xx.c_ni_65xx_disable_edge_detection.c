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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ni_65xx_update_edge_detection (struct comedi_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ni_65xx_disable_edge_detection(struct comedi_device *dev)
{
	/* clear edge detection for channels 0 to 31 */
	ni_65xx_update_edge_detection(dev, 0, 0, 0);
	/* clear edge detection for channels 32 to 63 */
	ni_65xx_update_edge_detection(dev, 32, 0, 0);
	/* clear edge detection for channels 64 to 95 */
	ni_65xx_update_edge_detection(dev, 64, 0, 0);
}