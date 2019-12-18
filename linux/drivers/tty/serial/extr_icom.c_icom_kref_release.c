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
struct kref {int dummy; } ;
struct icom_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  icom_remove_adapter (struct icom_adapter*) ; 
 struct icom_adapter* to_icom_adapter (struct kref*) ; 

__attribute__((used)) static void icom_kref_release(struct kref *kref)
{
	struct icom_adapter *icom_adapter;

	icom_adapter = to_icom_adapter(kref);
	icom_remove_adapter(icom_adapter);
}