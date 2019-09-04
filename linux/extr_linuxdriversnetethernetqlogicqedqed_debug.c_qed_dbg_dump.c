#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {TYPE_3__* cdev; } ;
struct qed_dbg_feature {int buf_size; int /*<<< orphan*/  dumped_dwords; int /*<<< orphan*/ * dump_buf; } ;
typedef  enum qed_dbg_features { ____Placeholder_qed_dbg_features } qed_dbg_features ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;
struct TYPE_4__ {struct qed_dbg_feature* features; } ;
struct TYPE_6__ {TYPE_1__ dbg_params; } ;
struct TYPE_5__ {int (* get_size ) (struct qed_hwfn*,struct qed_ptt*,int*) ;int (* perform_dump ) (struct qed_hwfn*,struct qed_ptt*,int*,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int DBG_STATUS_NVRAM_GET_IMAGE_FAILED ; 
 int DBG_STATUS_OK ; 
 int DBG_STATUS_VIRT_MEM_ALLOC_FAILED ; 
 int /*<<< orphan*/  DP_NOTICE (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int format_feature (struct qed_hwfn*,int) ; 
 TYPE_2__* qed_features_lookup ; 
 int stub1 (struct qed_hwfn*,struct qed_ptt*,int*) ; 
 int stub2 (struct qed_hwfn*,struct qed_ptt*,int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vmalloc (int) ; 

__attribute__((used)) static enum dbg_status qed_dbg_dump(struct qed_hwfn *p_hwfn,
				    struct qed_ptt *p_ptt,
				    enum qed_dbg_features feature_idx)
{
	struct qed_dbg_feature *feature =
	    &p_hwfn->cdev->dbg_params.features[feature_idx];
	u32 buf_size_dwords;
	enum dbg_status rc;

	DP_NOTICE(p_hwfn->cdev, "Collecting a debug feature [\"%s\"]\n",
		  qed_features_lookup[feature_idx].name);

	/* Dump_buf was already allocated need to free (this can happen if dump
	 * was called but file was never read).
	 * We can't use the buffer as is since size may have changed.
	 */
	if (feature->dump_buf) {
		vfree(feature->dump_buf);
		feature->dump_buf = NULL;
	}

	/* Get buffer size from hsi, allocate accordingly, and perform the
	 * dump.
	 */
	rc = qed_features_lookup[feature_idx].get_size(p_hwfn, p_ptt,
						       &buf_size_dwords);
	if (rc != DBG_STATUS_OK && rc != DBG_STATUS_NVRAM_GET_IMAGE_FAILED)
		return rc;
	feature->buf_size = buf_size_dwords * sizeof(u32);
	feature->dump_buf = vmalloc(feature->buf_size);
	if (!feature->dump_buf)
		return DBG_STATUS_VIRT_MEM_ALLOC_FAILED;

	rc = qed_features_lookup[feature_idx].
		perform_dump(p_hwfn, p_ptt, (u32 *)feature->dump_buf,
			     feature->buf_size / sizeof(u32),
			     &feature->dumped_dwords);

	/* If mcp is stuck we get DBG_STATUS_NVRAM_GET_IMAGE_FAILED error.
	 * In this case the buffer holds valid binary data, but we wont able
	 * to parse it (since parsing relies on data in NVRAM which is only
	 * accessible when MFW is responsive). skip the formatting but return
	 * success so that binary data is provided.
	 */
	if (rc == DBG_STATUS_NVRAM_GET_IMAGE_FAILED)
		return DBG_STATUS_OK;

	if (rc != DBG_STATUS_OK)
		return rc;

	/* Format output */
	rc = format_feature(p_hwfn, feature_idx);
	return rc;
}