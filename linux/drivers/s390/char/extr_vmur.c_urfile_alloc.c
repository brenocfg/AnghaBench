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
struct urfile {int /*<<< orphan*/  dev_reclen; struct urdev* urd; } ;
struct urdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TRACE (char*,struct urdev*,struct urfile*,int /*<<< orphan*/ ) ; 
 struct urfile* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct urfile *urfile_alloc(struct urdev *urd)
{
	struct urfile *urf;

	urf = kzalloc(sizeof(struct urfile), GFP_KERNEL);
	if (!urf)
		return NULL;
	urf->urd = urd;

	TRACE("urfile_alloc: urd=%p urf=%p rl=%zu\n", urd, urf,
	      urf->dev_reclen);

	return urf;
}