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
struct pstore_info {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ erst_disable ; 
 int erst_get_record_id_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_pos ; 

__attribute__((used)) static int erst_open_pstore(struct pstore_info *psi)
{
	int rc;

	if (erst_disable)
		return -ENODEV;

	rc = erst_get_record_id_begin(&reader_pos);

	return rc;
}