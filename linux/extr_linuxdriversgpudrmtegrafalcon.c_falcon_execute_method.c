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
typedef  int u32 ;
struct falcon {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALCON_UCLASS_METHOD_DATA ; 
 int /*<<< orphan*/  FALCON_UCLASS_METHOD_OFFSET ; 
 int /*<<< orphan*/  falcon_writel (struct falcon*,int,int /*<<< orphan*/ ) ; 

void falcon_execute_method(struct falcon *falcon, u32 method, u32 data)
{
	falcon_writel(falcon, method >> 2, FALCON_UCLASS_METHOD_OFFSET);
	falcon_writel(falcon, data, FALCON_UCLASS_METHOD_DATA);
}