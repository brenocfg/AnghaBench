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
typedef  int u64 ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int MLX5_IB_UMR_OCTOWORD ; 
 int /*<<< orphan*/  MLX5_IB_UMR_XLT_ALIGNMENT ; 

__attribute__((used)) static u64 get_xlt_octo(u64 bytes)
{
	return ALIGN(bytes, MLX5_IB_UMR_XLT_ALIGNMENT) /
	       MLX5_IB_UMR_OCTOWORD;
}