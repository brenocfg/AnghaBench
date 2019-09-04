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
struct qed_hwfn {int /*<<< orphan*/  p_arfs_ptt; } ;
struct qed_dev {int dummy; } ;
struct qed_arfs_config_params {int tcp; int udp; int ipv4; int ipv6; int mode; } ;
typedef  enum qed_filter_config_mode { ____Placeholder_qed_filter_config_mode } qed_filter_config_mode ;
typedef  int /*<<< orphan*/  arfs_config_params ;

/* Variables and functions */
 struct qed_hwfn* QED_LEADING_HWFN (struct qed_dev*) ; 
 int /*<<< orphan*/  memset (struct qed_arfs_config_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_arfs_mode_configure (struct qed_hwfn*,int /*<<< orphan*/ ,struct qed_arfs_config_params*) ; 

__attribute__((used)) static int qed_configure_arfs_searcher(struct qed_dev *cdev,
				       enum qed_filter_config_mode mode)
{
	struct qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	struct qed_arfs_config_params arfs_config_params;

	memset(&arfs_config_params, 0, sizeof(arfs_config_params));
	arfs_config_params.tcp = true;
	arfs_config_params.udp = true;
	arfs_config_params.ipv4 = true;
	arfs_config_params.ipv6 = true;
	arfs_config_params.mode = mode;
	qed_arfs_mode_configure(p_hwfn, p_hwfn->p_arfs_ptt,
				&arfs_config_params);
	return 0;
}