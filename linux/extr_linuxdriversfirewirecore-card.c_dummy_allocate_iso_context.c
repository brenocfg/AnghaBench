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
struct fw_iso_context {int dummy; } ;
struct fw_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct fw_iso_context* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fw_iso_context *dummy_allocate_iso_context(struct fw_card *card,
				int type, int channel, size_t header_size)
{
	return ERR_PTR(-ENODEV);
}