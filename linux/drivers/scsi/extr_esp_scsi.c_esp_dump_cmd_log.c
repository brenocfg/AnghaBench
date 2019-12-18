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
struct esp_event_ent {scalar_t__ type; int /*<<< orphan*/  event; int /*<<< orphan*/  select_state; int /*<<< orphan*/  ireg; int /*<<< orphan*/  sreg2; int /*<<< orphan*/  seqreg; int /*<<< orphan*/  sreg; int /*<<< orphan*/  val; } ;
struct esp {int esp_event_cur; int /*<<< orphan*/  host; struct esp_event_ent* esp_event_log; } ;

/* Variables and functions */
 int ESP_EVENT_LOG_SZ ; 
 scalar_t__ ESP_EVENT_TYPE_CMD ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void esp_dump_cmd_log(struct esp *esp)
{
	int idx = esp->esp_event_cur;
	int stop = idx;

	shost_printk(KERN_INFO, esp->host, "Dumping command log\n");
	do {
		struct esp_event_ent *p = &esp->esp_event_log[idx];

		shost_printk(KERN_INFO, esp->host,
			     "ent[%d] %s val[%02x] sreg[%02x] seqreg[%02x] "
			     "sreg2[%02x] ireg[%02x] ss[%02x] event[%02x]\n",
			     idx,
			     p->type == ESP_EVENT_TYPE_CMD ? "CMD" : "EVENT",
			     p->val, p->sreg, p->seqreg,
			     p->sreg2, p->ireg, p->select_state, p->event);

		idx = (idx + 1) & (ESP_EVENT_LOG_SZ - 1);
	} while (idx != stop);
}