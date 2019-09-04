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
struct mddev {int dummy; } ;
struct bitmap {int dummy; } ;

/* Variables and functions */
 struct bitmap* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct bitmap*) ; 
 int PTR_ERR (struct bitmap*) ; 
 struct bitmap* md_bitmap_create (struct mddev*,int) ; 
 int /*<<< orphan*/  md_bitmap_free (struct bitmap*) ; 
 int md_bitmap_init_from_disk (struct bitmap*,int /*<<< orphan*/ ) ; 

struct bitmap *get_bitmap_from_slot(struct mddev *mddev, int slot)
{
	int rv = 0;
	struct bitmap *bitmap;

	bitmap = md_bitmap_create(mddev, slot);
	if (IS_ERR(bitmap)) {
		rv = PTR_ERR(bitmap);
		return ERR_PTR(rv);
	}

	rv = md_bitmap_init_from_disk(bitmap, 0);
	if (rv) {
		md_bitmap_free(bitmap);
		return ERR_PTR(rv);
	}

	return bitmap;
}