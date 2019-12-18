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
typedef  int /*<<< orphan*/  val ;
struct wsm_protected_mgmt_policy {scalar_t__ encryptionForAuthFrame; scalar_t__ unprotectedMgmtFramesAllowed; scalar_t__ protectedMgmtEnable; } ;
struct cw1200_common {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  WSM_MIB_ID_PROTECTED_MGMT_POLICY ; 
 int /*<<< orphan*/  __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int wsm_write_mib (struct cw1200_common*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int wsm_set_protected_mgmt_policy(struct cw1200_common *priv,
		struct wsm_protected_mgmt_policy *arg)
{
	__le32 val = 0;
	int ret;
	if (arg->protectedMgmtEnable)
		val |= __cpu_to_le32(BIT(0));
	if (arg->unprotectedMgmtFramesAllowed)
		val |= __cpu_to_le32(BIT(1));
	if (arg->encryptionForAuthFrame)
		val |= __cpu_to_le32(BIT(2));
	ret = wsm_write_mib(priv, WSM_MIB_ID_PROTECTED_MGMT_POLICY,
			&val, sizeof(val));
	return ret;
}