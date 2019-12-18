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
struct inode {struct bfad_port_s* i_private; } ;
struct file {struct bfad_debug_info* private_data; } ;
struct bfad_s {scalar_t__ trcmod; } ;
struct bfad_port_s {struct bfad_s* bfad; } ;
struct bfad_debug_info {int buffer_len; void* debug_buffer; } ;
struct bfa_trc_mod_s {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct bfad_debug_info* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bfad_debugfs_open_drvtrc(struct inode *inode, struct file *file)
{
	struct bfad_port_s *port = inode->i_private;
	struct bfad_s *bfad = port->bfad;
	struct bfad_debug_info *debug;

	debug = kzalloc(sizeof(struct bfad_debug_info), GFP_KERNEL);
	if (!debug)
		return -ENOMEM;

	debug->debug_buffer = (void *) bfad->trcmod;
	debug->buffer_len = sizeof(struct bfa_trc_mod_s);

	file->private_data = debug;

	return 0;
}