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
struct drm_device {struct ast_private* dev_private; } ;
struct ast_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AST_IO_CRTC_PORT ; 
 int /*<<< orphan*/  ast_set_index_reg_mask (struct ast_private*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_cmd_trigger (struct ast_private*) ; 
 int /*<<< orphan*/  send_ack (struct ast_private*) ; 
 int /*<<< orphan*/  send_nack (struct ast_private*) ; 
 int /*<<< orphan*/  set_cmd_trigger (struct ast_private*) ; 
 scalar_t__ wait_ack (struct ast_private*) ; 
 scalar_t__ wait_nack (struct ast_private*) ; 

__attribute__((used)) static bool ast_write_cmd(struct drm_device *dev, u8 data)
{
	struct ast_private *ast = dev->dev_private;
	int retry = 0;
	if (wait_nack(ast)) {
		send_nack(ast);
		ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x9a, 0x00, data);
		send_ack(ast);
		set_cmd_trigger(ast);
		do {
			if (wait_ack(ast)) {
				clear_cmd_trigger(ast);
				send_nack(ast);
				return true;
			}
		} while (retry++ < 100);
	}
	clear_cmd_trigger(ast);
	send_nack(ast);
	return false;
}