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
struct cdv_intel_dp_m_n {int tu; int gmch_m; int gmch_n; int link_m; int link_n; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdv_intel_reduce_ratio (int*,int*) ; 

__attribute__((used)) static void
cdv_intel_dp_compute_m_n(int bpp,
		     int nlanes,
		     int pixel_clock,
		     int link_clock,
		     struct cdv_intel_dp_m_n *m_n)
{
	m_n->tu = 64;
	m_n->gmch_m = (pixel_clock * bpp + 7) >> 3;
	m_n->gmch_n = link_clock * nlanes;
	cdv_intel_reduce_ratio(&m_n->gmch_m, &m_n->gmch_n);
	m_n->link_m = pixel_clock;
	m_n->link_n = link_clock;
	cdv_intel_reduce_ratio(&m_n->link_m, &m_n->link_n);
}