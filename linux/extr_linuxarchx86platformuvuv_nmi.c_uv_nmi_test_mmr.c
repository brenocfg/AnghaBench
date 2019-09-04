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
struct uv_hub_nmi_s {int nmi_value; int /*<<< orphan*/  read_mmr_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nmi_mmr ; 
 int nmi_mmr_pending ; 
 int uv_read_local_mmr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int uv_nmi_test_mmr(struct uv_hub_nmi_s *hub_nmi)
{
	hub_nmi->nmi_value = uv_read_local_mmr(nmi_mmr);
	atomic_inc(&hub_nmi->read_mmr_count);
	return !!(hub_nmi->nmi_value & nmi_mmr_pending);
}