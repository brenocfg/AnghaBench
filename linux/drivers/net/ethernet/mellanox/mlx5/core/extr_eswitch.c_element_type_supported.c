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
struct mlx5_eswitch {struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ELEMENT_TYPE_CAP_MASK_PARA_VPORT_TC ; 
 int ELEMENT_TYPE_CAP_MASK_TASR ; 
 int ELEMENT_TYPE_CAP_MASK_VPORT ; 
 int ELEMENT_TYPE_CAP_MASK_VPORT_TC ; 
 int MLX5_CAP_QOS (struct mlx5_core_dev const*,int /*<<< orphan*/ ) ; 
#define  SCHEDULING_CONTEXT_ELEMENT_TYPE_PARA_VPORT_TC 131 
#define  SCHEDULING_CONTEXT_ELEMENT_TYPE_TSAR 130 
#define  SCHEDULING_CONTEXT_ELEMENT_TYPE_VPORT 129 
#define  SCHEDULING_CONTEXT_ELEMENT_TYPE_VPORT_TC 128 
 int /*<<< orphan*/  esw_element_type ; 

__attribute__((used)) static bool element_type_supported(struct mlx5_eswitch *esw, int type)
{
	const struct mlx5_core_dev *dev = esw->dev;

	switch (type) {
	case SCHEDULING_CONTEXT_ELEMENT_TYPE_TSAR:
		return MLX5_CAP_QOS(dev, esw_element_type) &
		       ELEMENT_TYPE_CAP_MASK_TASR;
	case SCHEDULING_CONTEXT_ELEMENT_TYPE_VPORT:
		return MLX5_CAP_QOS(dev, esw_element_type) &
		       ELEMENT_TYPE_CAP_MASK_VPORT;
	case SCHEDULING_CONTEXT_ELEMENT_TYPE_VPORT_TC:
		return MLX5_CAP_QOS(dev, esw_element_type) &
		       ELEMENT_TYPE_CAP_MASK_VPORT_TC;
	case SCHEDULING_CONTEXT_ELEMENT_TYPE_PARA_VPORT_TC:
		return MLX5_CAP_QOS(dev, esw_element_type) &
		       ELEMENT_TYPE_CAP_MASK_PARA_VPORT_TC;
	}
	return false;
}