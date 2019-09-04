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

/* Variables and functions */
 scalar_t__ MVPP2_QDIST_MULTI_MODE ; 
 scalar_t__ queue_mode ; 

__attribute__((used)) static bool mvpp22_rss_is_supported(void)
{
	return queue_mode == MVPP2_QDIST_MULTI_MODE;
}