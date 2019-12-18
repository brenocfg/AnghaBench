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
struct smt_para {int p_type; int p_len; } ;
struct smt_header {int smt_len; } ;
struct s_smc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB_SMT (char*,int) ; 
 int PARA_LEN ; 
 int /*<<< orphan*/  SK_UNUSED (struct s_smc*) ; 
 int SMT_P_ECHODATA ; 

void *sm_to_para(struct s_smc *smc, struct smt_header *sm, int para)
{
	char	*p ;
	int	len ;
	int	plen ;
	void	*found = NULL;

	SK_UNUSED(smc) ;

	len = sm->smt_len ;
	p = (char *)(sm+1) ;		/* pointer to info */
	while (len > 0 ) {
		if (((struct smt_para *)p)->p_type == para)
			found = (void *) p ;
		plen = ((struct smt_para *)p)->p_len + PARA_LEN ;
		p += plen ;
		len -= plen ;
		if (len < 0) {
			DB_SMT("SMT : sm_to_para - length error %d", plen);
			return NULL;
		}
		if ((plen & 3) && (para != SMT_P_ECHODATA)) {
			DB_SMT("SMT : sm_to_para - odd length %d", plen);
			return NULL;
		}
		if (found)
			return found;
	}
	return NULL;
}