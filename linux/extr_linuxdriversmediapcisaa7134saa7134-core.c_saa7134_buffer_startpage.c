#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int index; } ;
struct TYPE_3__ {TYPE_2__ vb2_buf; } ;
struct saa7134_buf {TYPE_1__ vb2; } ;

/* Variables and functions */
 int saa7134_buffer_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_plane_size (TYPE_2__*,int /*<<< orphan*/ ) ; 

int saa7134_buffer_startpage(struct saa7134_buf *buf)
{
	return saa7134_buffer_pages(vb2_plane_size(&buf->vb2.vb2_buf, 0))
			* buf->vb2.vb2_buf.index;
}