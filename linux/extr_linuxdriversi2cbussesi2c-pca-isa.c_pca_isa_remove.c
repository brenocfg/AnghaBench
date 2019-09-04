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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_SIZE ; 
 int /*<<< orphan*/  base ; 
 int /*<<< orphan*/  disable_irq (int) ; 
 int /*<<< orphan*/  free_irq (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int irq ; 
 int /*<<< orphan*/  pca_isa_ops ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pca_isa_remove(struct device *dev, unsigned int id)
{
	i2c_del_adapter(&pca_isa_ops);

	if (irq > -1) {
		disable_irq(irq);
		free_irq(irq, &pca_isa_ops);
	}
	release_region(base, IO_SIZE);

	return 0;
}