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
typedef  enum port { ____Placeholder_port } port ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;

/* Variables and functions */
 int DPLL_ID_ICL_MGPLL1 ; 
 int PORT_C ; 

__attribute__((used)) static enum intel_dpll_id icl_port_to_mg_pll_id(enum port port)
{
	return port - PORT_C + DPLL_ID_ICL_MGPLL1;
}