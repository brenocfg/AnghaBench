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
typedef  int /*<<< orphan*/  u64 ;
struct hnae3_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hclgevf_tqps_get_stats (struct hnae3_handle*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclgevf_get_stats(struct hnae3_handle *handle, u64 *data)
{
	hclgevf_tqps_get_stats(handle, data);
}