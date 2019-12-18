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
struct ni_private {int /*<<< orphan*/  routing_tables; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */
 unsigned int ni_get_valid_routes (int /*<<< orphan*/ *,unsigned int,unsigned int*) ; 

__attribute__((used)) static unsigned int _ni_get_valid_routes(struct comedi_device *dev,
					 unsigned int n_pairs,
					 unsigned int *pair_data)
{
	struct ni_private *devpriv = dev->private;

	return ni_get_valid_routes(&devpriv->routing_tables, n_pairs,
				   pair_data);
}