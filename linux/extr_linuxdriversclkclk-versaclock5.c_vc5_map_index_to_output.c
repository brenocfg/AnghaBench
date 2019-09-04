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
typedef  enum vc5_model { ____Placeholder_vc5_model } vc5_model ;

/* Variables and functions */
#define  IDT_VC5_5P49V5923 132 
#define  IDT_VC5_5P49V5925 131 
#define  IDT_VC5_5P49V5933 130 
#define  IDT_VC5_5P49V5935 129 
#define  IDT_VC6_5P49V6901 128 

__attribute__((used)) static int vc5_map_index_to_output(const enum vc5_model model,
				   const unsigned int n)
{
	switch (model) {
	case IDT_VC5_5P49V5933:
		return (n == 0) ? 0 : 3;
	case IDT_VC5_5P49V5923:
	case IDT_VC5_5P49V5925:
	case IDT_VC5_5P49V5935:
	case IDT_VC6_5P49V6901:
	default:
		return n;
	}
}