#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct cas {TYPE_1__*** rx_pages; } ;
struct TYPE_5__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ cas_page_t ;

/* Variables and functions */
 int /*<<< orphan*/  RX_USED_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* cas_page_spare (struct cas*,int const) ; 
 int page_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static cas_page_t *cas_page_swap(struct cas *cp, const int ring,
				 const int index)
{
	cas_page_t **page0 = cp->rx_pages[0];
	cas_page_t **page1 = cp->rx_pages[1];

	/* swap if buffer is in use */
	if (page_count(page0[index]->buffer) > 1) {
		cas_page_t *new = cas_page_spare(cp, index);
		if (new) {
			page1[index] = page0[index];
			page0[index] = new;
		}
	}
	RX_USED_SET(page0[index], 0);
	return page0[index];
}