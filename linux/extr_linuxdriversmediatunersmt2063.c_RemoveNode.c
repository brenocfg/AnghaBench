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
struct MT2063_ExclZone_t {struct MT2063_ExclZone_t* next_; } ;
struct MT2063_AvoidSpursData_t {int /*<<< orphan*/  nZones; struct MT2063_ExclZone_t* freeZones; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*) ; 

__attribute__((used)) static struct MT2063_ExclZone_t *RemoveNode(struct MT2063_AvoidSpursData_t
					    *pAS_Info,
					    struct MT2063_ExclZone_t *pPrevNode,
					    struct MT2063_ExclZone_t
					    *pNodeToRemove)
{
	struct MT2063_ExclZone_t *pNext = pNodeToRemove->next_;

	dprintk(2, "\n");

	/*  Make previous node point to the subsequent node  */
	if (pPrevNode != NULL)
		pPrevNode->next_ = pNext;

	/*  Add pNodeToRemove to the beginning of the freeZones  */
	pNodeToRemove->next_ = pAS_Info->freeZones;
	pAS_Info->freeZones = pNodeToRemove;

	/*  Decrement node count  */
	pAS_Info->nZones--;

	return pNext;
}