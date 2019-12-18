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
struct of_device_id {scalar_t__ data; } ;
struct fsl_spi_match_data {int type; } ;
struct device {scalar_t__ of_node; } ;

/* Variables and functions */
 int TYPE_FSL ; 
 int /*<<< orphan*/  of_fsl_spi_match ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int fsl_spi_get_type(struct device *dev)
{
	const struct of_device_id *match;

	if (dev->of_node) {
		match = of_match_node(of_fsl_spi_match, dev->of_node);
		if (match && match->data)
			return ((struct fsl_spi_match_data *)match->data)->type;
	}
	return TYPE_FSL;
}