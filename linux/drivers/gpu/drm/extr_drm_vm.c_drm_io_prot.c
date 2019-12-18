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
struct vm_area_struct {scalar_t__ vm_start; scalar_t__ vm_end; int /*<<< orphan*/  vm_flags; } ;
struct drm_local_map {scalar_t__ type; int flags; } ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 scalar_t__ _DRM_REGISTERS ; 
 int _DRM_WRITE_COMBINING ; 
 scalar_t__ efi_range_is_wc (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pgprot_decrypted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_get_page_prot (int /*<<< orphan*/ ) ; 

__attribute__((used)) static pgprot_t drm_io_prot(struct drm_local_map *map,
			    struct vm_area_struct *vma)
{
	pgprot_t tmp = vm_get_page_prot(vma->vm_flags);

	/* We don't want graphics memory to be mapped encrypted */
	tmp = pgprot_decrypted(tmp);

#if defined(__i386__) || defined(__x86_64__) || defined(__powerpc__) || \
    defined(__mips__)
	if (map->type == _DRM_REGISTERS && !(map->flags & _DRM_WRITE_COMBINING))
		tmp = pgprot_noncached(tmp);
	else
		tmp = pgprot_writecombine(tmp);
#elif defined(__ia64__)
	if (efi_range_is_wc(vma->vm_start, vma->vm_end -
				    vma->vm_start))
		tmp = pgprot_writecombine(tmp);
	else
		tmp = pgprot_noncached(tmp);
#elif defined(__sparc__) || defined(__arm__)
	tmp = pgprot_noncached(tmp);
#endif
	return tmp;
}