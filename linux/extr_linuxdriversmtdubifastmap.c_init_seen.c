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
struct ubi_device {int /*<<< orphan*/  peb_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 unsigned long* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubi_dbg_chk_fastmap (struct ubi_device*) ; 

__attribute__((used)) static inline unsigned long *init_seen(struct ubi_device *ubi)
{
	unsigned long *ret;

	if (!ubi_dbg_chk_fastmap(ubi))
		return NULL;

	ret = kcalloc(BITS_TO_LONGS(ubi->peb_count), sizeof(unsigned long),
		      GFP_KERNEL);
	if (!ret)
		return ERR_PTR(-ENOMEM);

	return ret;
}