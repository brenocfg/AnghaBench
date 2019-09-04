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
struct hns_ppe_cb {int dummy; } ;
struct hnae_handle {int dummy; } ;

/* Variables and functions */
 struct hns_ppe_cb* hns_get_ppe_cb (struct hnae_handle*) ; 
 int /*<<< orphan*/  hns_ppe_set_tso_enable (struct hns_ppe_cb*,int) ; 

__attribute__((used)) static void hns_ae_set_tso_stats(struct hnae_handle *handle, int enable)
{
	struct hns_ppe_cb *ppe_cb = hns_get_ppe_cb(handle);

	hns_ppe_set_tso_enable(ppe_cb, enable);
}