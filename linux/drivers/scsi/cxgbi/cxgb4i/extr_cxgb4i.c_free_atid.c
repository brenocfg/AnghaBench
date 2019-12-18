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
struct cxgbi_sock {int /*<<< orphan*/  atid; int /*<<< orphan*/  cdev; } ;
struct cxgb4_lld_info {int /*<<< orphan*/  tids; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTPF_HAS_ATID ; 
 int /*<<< orphan*/  cxgb4_free_atid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cxgb4_lld_info* cxgbi_cdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_sock_clear_flag (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ cxgbi_sock_flag (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_sock_put (struct cxgbi_sock*) ; 

__attribute__((used)) static inline void free_atid(struct cxgbi_sock *csk)
{
	struct cxgb4_lld_info *lldi = cxgbi_cdev_priv(csk->cdev);

	if (cxgbi_sock_flag(csk, CTPF_HAS_ATID)) {
		cxgb4_free_atid(lldi->tids, csk->atid);
		cxgbi_sock_clear_flag(csk, CTPF_HAS_ATID);
		cxgbi_sock_put(csk);
	}
}