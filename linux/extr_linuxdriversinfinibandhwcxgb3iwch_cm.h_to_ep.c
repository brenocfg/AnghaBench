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
struct iwch_ep {int dummy; } ;
struct iw_cm_id {struct iwch_ep* provider_data; } ;

/* Variables and functions */

__attribute__((used)) static inline struct iwch_ep *to_ep(struct iw_cm_id *cm_id)
{
	return cm_id->provider_data;
}