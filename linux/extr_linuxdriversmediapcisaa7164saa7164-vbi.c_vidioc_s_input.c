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
struct saa7164_vbi_fh {TYPE_1__* port; } ;
struct file {struct saa7164_vbi_fh* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  enc_port; } ;

/* Variables and functions */
 int saa7164_s_input (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int vidioc_s_input(struct file *file, void *priv, unsigned int i)
{
	struct saa7164_vbi_fh *fh = file->private_data;

	return saa7164_s_input(fh->port->enc_port, i);
}