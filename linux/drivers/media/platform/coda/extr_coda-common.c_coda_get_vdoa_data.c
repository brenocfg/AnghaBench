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
struct vdoa_data {int dummy; } ;
struct platform_device {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct vdoa_data* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct vdoa_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static struct vdoa_data *coda_get_vdoa_data(void)
{
	struct device_node *vdoa_node;
	struct platform_device *vdoa_pdev;
	struct vdoa_data *vdoa_data = NULL;

	vdoa_node = of_find_compatible_node(NULL, NULL, "fsl,imx6q-vdoa");
	if (!vdoa_node)
		return NULL;

	vdoa_pdev = of_find_device_by_node(vdoa_node);
	if (!vdoa_pdev)
		goto out;

	vdoa_data = platform_get_drvdata(vdoa_pdev);
	if (!vdoa_data)
		vdoa_data = ERR_PTR(-EPROBE_DEFER);

out:
	of_node_put(vdoa_node);

	return vdoa_data;
}