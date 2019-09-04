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
struct intel_link_m_n {int tu; int /*<<< orphan*/  link_n; int /*<<< orphan*/  link_m; int /*<<< orphan*/  gmch_n; int /*<<< orphan*/  gmch_m; } ;

/* Variables and functions */
 int /*<<< orphan*/  compute_m_n (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
intel_link_compute_m_n(int bits_per_pixel, int nlanes,
		       int pixel_clock, int link_clock,
		       struct intel_link_m_n *m_n,
		       bool reduce_m_n)
{
	m_n->tu = 64;

	compute_m_n(bits_per_pixel * pixel_clock,
		    link_clock * nlanes * 8,
		    &m_n->gmch_m, &m_n->gmch_n,
		    reduce_m_n);

	compute_m_n(pixel_clock, link_clock,
		    &m_n->link_m, &m_n->link_n,
		    reduce_m_n);
}