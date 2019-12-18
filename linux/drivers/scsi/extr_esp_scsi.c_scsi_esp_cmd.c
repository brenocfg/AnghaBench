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
typedef  int /*<<< orphan*/  u8 ;
struct esp_event_ent {int /*<<< orphan*/  val; int /*<<< orphan*/  type; } ;
struct esp {int esp_event_cur; struct esp_event_ent* esp_event_log; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_CMD ; 
 int ESP_EVENT_LOG_SZ ; 
 int /*<<< orphan*/  ESP_EVENT_TYPE_CMD ; 
 int /*<<< orphan*/  esp_log_command (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_log_fill_regs (struct esp*,struct esp_event_ent*) ; 
 int /*<<< orphan*/  esp_write8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void scsi_esp_cmd(struct esp *esp, u8 val)
{
	struct esp_event_ent *p;
	int idx = esp->esp_event_cur;

	p = &esp->esp_event_log[idx];
	p->type = ESP_EVENT_TYPE_CMD;
	p->val = val;
	esp_log_fill_regs(esp, p);

	esp->esp_event_cur = (idx + 1) & (ESP_EVENT_LOG_SZ - 1);

	esp_log_command("cmd[%02x]\n", val);
	esp_write8(val, ESP_CMD);
}