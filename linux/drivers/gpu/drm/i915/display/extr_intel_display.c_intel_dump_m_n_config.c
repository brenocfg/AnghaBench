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
struct intel_link_m_n {int /*<<< orphan*/  tu; int /*<<< orphan*/  link_n; int /*<<< orphan*/  link_m; int /*<<< orphan*/  gmch_n; int /*<<< orphan*/  gmch_m; } ;
struct intel_crtc_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,char const*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
intel_dump_m_n_config(const struct intel_crtc_state *pipe_config,
		      const char *id, unsigned int lane_count,
		      const struct intel_link_m_n *m_n)
{
	DRM_DEBUG_KMS("%s: lanes: %i; gmch_m: %u, gmch_n: %u, link_m: %u, link_n: %u, tu: %u\n",
		      id, lane_count,
		      m_n->gmch_m, m_n->gmch_n,
		      m_n->link_m, m_n->link_n, m_n->tu);
}