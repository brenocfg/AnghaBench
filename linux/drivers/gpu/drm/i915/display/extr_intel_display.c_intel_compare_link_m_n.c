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
struct intel_link_m_n {scalar_t__ tu; int /*<<< orphan*/  link_n; int /*<<< orphan*/  link_m; int /*<<< orphan*/  gmch_n; int /*<<< orphan*/  gmch_m; } ;

/* Variables and functions */
 scalar_t__ intel_compare_m_n (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
intel_compare_link_m_n(const struct intel_link_m_n *m_n,
		       const struct intel_link_m_n *m2_n2,
		       bool exact)
{
	return m_n->tu == m2_n2->tu &&
		intel_compare_m_n(m_n->gmch_m, m_n->gmch_n,
				  m2_n2->gmch_m, m2_n2->gmch_n, exact) &&
		intel_compare_m_n(m_n->link_m, m_n->link_n,
				  m2_n2->link_m, m2_n2->link_n, exact);
}