#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct qed_ptt {int dummy; } ;
struct qed_nvm_image_info {size_t num_images; TYPE_2__* image_att; } ;
struct TYPE_5__ {int valid; size_t num_images; TYPE_2__* image_att; } ;
struct qed_hwfn {TYPE_1__ nvm_info; } ;
struct bist_nvm_image_att {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*,...) ; 
 int /*<<< orphan*/  DP_INFO (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QED_MSG_SP ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* kmalloc_array (size_t,int,int /*<<< orphan*/ ) ; 
 int qed_mcp_bist_nvm_get_image_att (struct qed_hwfn*,struct qed_ptt*,TYPE_2__*,size_t) ; 
 int qed_mcp_bist_nvm_get_num_images (struct qed_hwfn*,struct qed_ptt*,size_t*) ; 
 struct qed_ptt* qed_ptt_acquire (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_ptt_release (struct qed_hwfn*,struct qed_ptt*) ; 

int qed_mcp_nvm_info_populate(struct qed_hwfn *p_hwfn)
{
	struct qed_nvm_image_info nvm_info;
	struct qed_ptt *p_ptt;
	int rc;
	u32 i;

	if (p_hwfn->nvm_info.valid)
		return 0;

	p_ptt = qed_ptt_acquire(p_hwfn);
	if (!p_ptt) {
		DP_ERR(p_hwfn, "failed to acquire ptt\n");
		return -EBUSY;
	}

	/* Acquire from MFW the amount of available images */
	nvm_info.num_images = 0;
	rc = qed_mcp_bist_nvm_get_num_images(p_hwfn,
					     p_ptt, &nvm_info.num_images);
	if (rc == -EOPNOTSUPP) {
		DP_INFO(p_hwfn, "DRV_MSG_CODE_BIST_TEST is not supported\n");
		goto out;
	} else if (rc || !nvm_info.num_images) {
		DP_ERR(p_hwfn, "Failed getting number of images\n");
		goto err0;
	}

	nvm_info.image_att = kmalloc_array(nvm_info.num_images,
					   sizeof(struct bist_nvm_image_att),
					   GFP_KERNEL);
	if (!nvm_info.image_att) {
		rc = -ENOMEM;
		goto err0;
	}

	/* Iterate over images and get their attributes */
	for (i = 0; i < nvm_info.num_images; i++) {
		rc = qed_mcp_bist_nvm_get_image_att(p_hwfn, p_ptt,
						    &nvm_info.image_att[i], i);
		if (rc) {
			DP_ERR(p_hwfn,
			       "Failed getting image index %d attributes\n", i);
			goto err1;
		}

		DP_VERBOSE(p_hwfn, QED_MSG_SP, "image index %d, size %x\n", i,
			   nvm_info.image_att[i].len);
	}
out:
	/* Update hwfn's nvm_info */
	if (nvm_info.num_images) {
		p_hwfn->nvm_info.num_images = nvm_info.num_images;
		kfree(p_hwfn->nvm_info.image_att);
		p_hwfn->nvm_info.image_att = nvm_info.image_att;
		p_hwfn->nvm_info.valid = true;
	}

	qed_ptt_release(p_hwfn, p_ptt);
	return 0;

err1:
	kfree(nvm_info.image_att);
err0:
	qed_ptt_release(p_hwfn, p_ptt);
	return rc;
}