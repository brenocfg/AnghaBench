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
struct qla27xx_fwdt_template {int /*<<< orphan*/  template_type; } ;

/* Variables and functions */
 scalar_t__ TEMPLATE_TYPE_FWDUMP ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
qla27xx_verify_template_header(struct qla27xx_fwdt_template *tmp)
{
	return le32_to_cpu(tmp->template_type) == TEMPLATE_TYPE_FWDUMP;
}