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
typedef  int /*<<< orphan*/  u32 ;
struct hnae3_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_RSS_KEY_SIZE ; 

__attribute__((used)) static u32 hclge_get_rss_key_size(struct hnae3_handle *handle)
{
	return HCLGE_RSS_KEY_SIZE;
}