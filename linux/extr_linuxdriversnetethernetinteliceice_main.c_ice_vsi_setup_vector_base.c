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
struct ice_vsi {int type; int num_q_vectors; int /*<<< orphan*/  base_vector; int /*<<< orphan*/  vsi_num; int /*<<< orphan*/  idx; struct ice_pf* back; } ;
struct ice_pf {TYPE_1__* pdev; int /*<<< orphan*/  irq_tracker; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOENT ; 
 int /*<<< orphan*/  ICE_FLAG_MSIX_ENA ; 
#define  ICE_VSI_PF 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ice_get_res (struct ice_pf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ice_vsi_setup_vector_base(struct ice_vsi *vsi)
{
	struct ice_pf *pf = vsi->back;
	int num_q_vectors = 0;

	if (vsi->base_vector) {
		dev_dbg(&pf->pdev->dev, "VSI %d has non-zero base vector %d\n",
			vsi->vsi_num, vsi->base_vector);
		return -EEXIST;
	}

	if (!test_bit(ICE_FLAG_MSIX_ENA, pf->flags))
		return -ENOENT;

	switch (vsi->type) {
	case ICE_VSI_PF:
		num_q_vectors = vsi->num_q_vectors;
		break;
	default:
		dev_warn(&vsi->back->pdev->dev, "Unknown VSI type %d\n",
			 vsi->type);
		break;
	}

	if (num_q_vectors)
		vsi->base_vector = ice_get_res(pf, pf->irq_tracker,
					       num_q_vectors, vsi->idx);

	if (vsi->base_vector < 0) {
		dev_err(&pf->pdev->dev,
			"Failed to get tracking for %d vectors for VSI %d, err=%d\n",
			num_q_vectors, vsi->vsi_num, vsi->base_vector);
		return -ENOENT;
	}

	return 0;
}