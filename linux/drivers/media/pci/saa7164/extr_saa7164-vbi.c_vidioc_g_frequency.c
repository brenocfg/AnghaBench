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
struct v4l2_frequency {int dummy; } ;
struct saa7164_vbi_fh {TYPE_1__* port; } ;
struct file {struct saa7164_vbi_fh* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  enc_port; } ;

/* Variables and functions */
 int saa7164_g_frequency (int /*<<< orphan*/ ,struct v4l2_frequency*) ; 

__attribute__((used)) static int vidioc_g_frequency(struct file *file, void *priv,
	struct v4l2_frequency *f)
{
	struct saa7164_vbi_fh *fh = file->private_data;

	return saa7164_g_frequency(fh->port->enc_port, f);
}