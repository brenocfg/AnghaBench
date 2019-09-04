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
struct vb2_queue {struct vb2_fileio_data* fileio; int /*<<< orphan*/  type; } ;
struct vb2_fileio_data {scalar_t__ count; int /*<<< orphan*/  memory; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  kfree (struct vb2_fileio_data*) ; 
 int /*<<< orphan*/  vb2_core_reqbufs (struct vb2_queue*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  vb2_core_streamoff (struct vb2_queue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __vb2_cleanup_fileio(struct vb2_queue *q)
{
	struct vb2_fileio_data *fileio = q->fileio;

	if (fileio) {
		vb2_core_streamoff(q, q->type);
		q->fileio = NULL;
		fileio->count = 0;
		vb2_core_reqbufs(q, fileio->memory, &fileio->count);
		kfree(fileio);
		dprintk(3, "file io emulator closed\n");
	}
	return 0;
}