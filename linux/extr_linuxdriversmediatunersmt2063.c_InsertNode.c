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
struct MT2063_AvoidSpursData_t {size_t nZones; struct MT2063_ExclZone_t* usedZones; struct MT2063_ExclZone_t* MT2063_ExclZones; struct MT2063_ExclZone_t* freeZones; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*) ; 

__attribute__((used)) static struct MT2063_ExclZone_t *InsertNode(struct MT2063_AvoidSpursData_t
					    *pAS_Info,
					    struct MT2063_ExclZone_t *pPrevNode)
{
	struct MT2063_ExclZone_t *pNode;

	dprintk(2, "\n");

	/*  Check for a node in the free list  */
	if (pAS_Info->freeZones != NULL) {
		/*  Use one from the free list  */
		pNode = pAS_Info->freeZones;
		pAS_Info->freeZones = pNode->next_;
	} else {
		/*  Grab a node from the array  */
		pNode = &pAS_Info->MT2063_ExclZones[pAS_Info->nZones];
	}

	if (pPrevNode != NULL) {
		pNode->next_ = pPrevNode->next_;
		pPrevNode->next_ = pNode;
	} else {		/*  insert at the beginning of the list  */

		pNode->next_ = pAS_Info->usedZones;
		pAS_Info->usedZones = pNode;
	}

	pAS_Info->nZones++;
	return pNode;
}