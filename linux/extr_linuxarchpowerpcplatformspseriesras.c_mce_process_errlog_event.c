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
struct rtas_error_log {int dummy; } ;
struct irq_work {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_TYPE_RTAS_LOG ; 
 struct rtas_error_log* fwnmi_get_errlog () ; 
 int /*<<< orphan*/  log_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mce_process_errlog_event(struct irq_work *work)
{
	struct rtas_error_log *err;

	err = fwnmi_get_errlog();
	log_error((char *)err, ERR_TYPE_RTAS_LOG, 0);
}