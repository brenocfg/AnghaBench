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
struct cacheinfo {int attributes; scalar_t__ type; int /*<<< orphan*/  ways_of_associativity; int /*<<< orphan*/  number_of_sets; int /*<<< orphan*/  coherency_line_size; int /*<<< orphan*/  size; struct acpi_pptt_processor* fw_token; } ;
struct acpi_pptt_processor {int dummy; } ;
struct acpi_pptt_cache {int flags; int attributes; int /*<<< orphan*/  associativity; int /*<<< orphan*/  number_of_sets; int /*<<< orphan*/  line_size; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int ACPI_PPTT_ALLOCATION_TYPE_VALID ; 
 int ACPI_PPTT_ASSOCIATIVITY_VALID ; 
#define  ACPI_PPTT_CACHE_POLICY_WB 133 
#define  ACPI_PPTT_CACHE_POLICY_WT 132 
#define  ACPI_PPTT_CACHE_READ_ALLOCATE 131 
#define  ACPI_PPTT_CACHE_RW_ALLOCATE 130 
#define  ACPI_PPTT_CACHE_RW_ALLOCATE_ALT 129 
 int ACPI_PPTT_CACHE_TYPE_VALID ; 
#define  ACPI_PPTT_CACHE_WRITE_ALLOCATE 128 
 int ACPI_PPTT_LINE_SIZE_VALID ; 
 int ACPI_PPTT_MASK_ALLOCATION_TYPE ; 
 int ACPI_PPTT_MASK_WRITE_POLICY ; 
 int ACPI_PPTT_NUMBER_OF_SETS_VALID ; 
 int ACPI_PPTT_SIZE_PROPERTY_VALID ; 
 int ACPI_PPTT_WRITE_POLICY_VALID ; 
 int CACHE_READ_ALLOCATE ; 
 scalar_t__ CACHE_TYPE_NOCACHE ; 
 scalar_t__ CACHE_TYPE_UNIFIED ; 
 int CACHE_WRITE_ALLOCATE ; 
 int CACHE_WRITE_BACK ; 
 int CACHE_WRITE_THROUGH ; 

__attribute__((used)) static void update_cache_properties(struct cacheinfo *this_leaf,
				    struct acpi_pptt_cache *found_cache,
				    struct acpi_pptt_processor *cpu_node)
{
	this_leaf->fw_token = cpu_node;
	if (found_cache->flags & ACPI_PPTT_SIZE_PROPERTY_VALID)
		this_leaf->size = found_cache->size;
	if (found_cache->flags & ACPI_PPTT_LINE_SIZE_VALID)
		this_leaf->coherency_line_size = found_cache->line_size;
	if (found_cache->flags & ACPI_PPTT_NUMBER_OF_SETS_VALID)
		this_leaf->number_of_sets = found_cache->number_of_sets;
	if (found_cache->flags & ACPI_PPTT_ASSOCIATIVITY_VALID)
		this_leaf->ways_of_associativity = found_cache->associativity;
	if (found_cache->flags & ACPI_PPTT_WRITE_POLICY_VALID) {
		switch (found_cache->attributes & ACPI_PPTT_MASK_WRITE_POLICY) {
		case ACPI_PPTT_CACHE_POLICY_WT:
			this_leaf->attributes = CACHE_WRITE_THROUGH;
			break;
		case ACPI_PPTT_CACHE_POLICY_WB:
			this_leaf->attributes = CACHE_WRITE_BACK;
			break;
		}
	}
	if (found_cache->flags & ACPI_PPTT_ALLOCATION_TYPE_VALID) {
		switch (found_cache->attributes & ACPI_PPTT_MASK_ALLOCATION_TYPE) {
		case ACPI_PPTT_CACHE_READ_ALLOCATE:
			this_leaf->attributes |= CACHE_READ_ALLOCATE;
			break;
		case ACPI_PPTT_CACHE_WRITE_ALLOCATE:
			this_leaf->attributes |= CACHE_WRITE_ALLOCATE;
			break;
		case ACPI_PPTT_CACHE_RW_ALLOCATE:
		case ACPI_PPTT_CACHE_RW_ALLOCATE_ALT:
			this_leaf->attributes |=
				CACHE_READ_ALLOCATE | CACHE_WRITE_ALLOCATE;
			break;
		}
	}
	/*
	 * If cache type is NOCACHE, then the cache hasn't been specified
	 * via other mechanisms.  Update the type if a cache type has been
	 * provided.
	 *
	 * Note, we assume such caches are unified based on conventional system
	 * design and known examples.  Significant work is required elsewhere to
	 * fully support data/instruction only type caches which are only
	 * specified in PPTT.
	 */
	if (this_leaf->type == CACHE_TYPE_NOCACHE &&
	    found_cache->flags & ACPI_PPTT_CACHE_TYPE_VALID)
		this_leaf->type = CACHE_TYPE_UNIFIED;
}