#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_msi_priv_data {int /*<<< orphan*/  (* write_msg ) (struct msi_desc*,struct msi_msg*) ;} ;
struct msi_msg {int dummy; } ;
struct TYPE_2__ {struct platform_msi_priv_data* msi_priv_data; } ;
struct msi_desc {TYPE_1__ platform; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 struct msi_desc* irq_data_get_msi_desc (struct irq_data*) ; 
 int /*<<< orphan*/  stub1 (struct msi_desc*,struct msi_msg*) ; 

__attribute__((used)) static void platform_msi_write_msg(struct irq_data *data, struct msi_msg *msg)
{
	struct msi_desc *desc = irq_data_get_msi_desc(data);
	struct platform_msi_priv_data *priv_data;

	priv_data = desc->platform.msi_priv_data;

	priv_data->write_msg(desc, msg);
}