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
struct mconsole_command {int /*<<< orphan*/  command; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct mc_request {TYPE_1__ request; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct mconsole_command*) ; 
 struct mconsole_command* commands ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mconsole_command *mconsole_parse(struct mc_request *req)
{
	struct mconsole_command *cmd;
	int i;

	for (i = 0; i < ARRAY_SIZE(commands); i++) {
		cmd = &commands[i];
		if (!strncmp(req->request.data, cmd->command,
			    strlen(cmd->command))) {
			return cmd;
		}
	}
	return NULL;
}