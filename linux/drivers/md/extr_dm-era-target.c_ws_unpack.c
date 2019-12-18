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
struct writeset_metadata {int /*<<< orphan*/  root; int /*<<< orphan*/  nr_bits; } ;
struct writeset_disk {int /*<<< orphan*/  root; int /*<<< orphan*/  nr_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ws_unpack(const struct writeset_disk *disk, struct writeset_metadata *core)
{
	core->nr_bits = le32_to_cpu(disk->nr_bits);
	core->root = le64_to_cpu(disk->root);
}